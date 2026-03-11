workspace "Event Management System" "Система управления мероприятиями" {
    model {
        eventManager = person "Организатор мероприятий" "Человек, отвечающий за организацию мероприятий." "Person"
        guest = person "Гость" "Человек, участвующий в мероприятии." "Person"

        billingSystem = softwareSystem "Billing Service" "Внешняя система платежей." "External"
        mailServers = softwareSystem "Mail Servers" "Почтовые сервера пользователей" "External"
        appClients = softwareSystem "App Clients" "Клиентские приложения пользователей (могут быть мобильные, desktop или web)" "External"

        eventSystem = softwareSystem "Event Management System" {
            gateway = container "API Gateway" "Проксирование запросов, балансировка нагрузки и управление SSL сертификатами" "Nginx" "Container"

            eventService = container "Event Service" "Управление мероприятиями" "C++/Userver" "Container"
            layoutDesignService = container "Layout design Service" "Конструирование макетов сообщений" "C++/Userver" "Container"
            mailService = container "Mail Message Service" "Отправка сообщений на почтовые сервера пользователей" "C++/UServer" "Container"
            appService = container "App Message Service" "Отправка сообщений на приложения пользователей" "C++/Userver" "Container"
            accountService = container "Account Service" "Управление аккаунтами пользователей" "C++/Userver" "Container"
            notificationService = container "Notification Service" "Отправка уведомлений о мероприятиях по расписанию" "C++/Userver" "Container"

            eventDb = container "Event Database" "Реляционное хранилище мероприятий." "PostgreSQL" "Database" 
            eventObjectStorage = container "Event Object Storage" "Объектное хранилище мероприятий" "S3/minio" "Database"
            accountDb = container "Account Database""Реляционное хранилище аккаунтов пользователей." "PostgreSQL" "Database"
            layoutObjectStorage = container "Layout Object Storage" "Объектное хранилище макетов сообщений." "S3/minio" "Database"
            layoutCache = container "Layout Cache" "Кэширование еще не созданных макетов сообщений." "Redis" "Database"
            notificationCache = container "Notification Cache" "Кэширование расписания уведомлений." "Redis" "Database"
            appCache = container "App Cache" "Кэширование сообщений для отправки на приложения" "Redis" "Database"
            
            messageSubject = container "Message Subject" "Брокер доставки сообщений" "Nats" "Broker"
            notificationSubject = container "Notification Subject" "Брокер доставки уведомлений" "Nats" "Broker"
        }

        eventManager -> gateway "REST API" "HTTPS/JSON"
        eventManager -> gateway "WebSocket Соединение" "WSS/JSON"
        guest -> gateway "REST API" "HTTPS/JSON"

        billingSystem -> gateway "Подтверждение платежа" "HTTP/JSON"

        gateway -> accountService "Авторизация" "HTTP/JSON"
        gateway -> eventService "Создание мероприятий" "WS/JSON"
        gateway -> eventService "Работа с мероприятиями" "HTTP/JSON"
        gateway -> layoutDesignService "Создание/изменение макетов сообщений" "WS/JSON"

        accountService -> billingSystem "Платеж" "HTTPS/JSON"
        accountService -> accountDb "Сохраниение записей об аккаунтах" "TCP/SQL"
        
        eventService -> eventDb "Сохранение записей о мероприятиях" "TCP/SQL"
        eventService -> eventObjectStorage "Сохранение файлов мероприятий" "TCP"
        eventService -> layoutDesignService "Получение макетов сообщений" "HTTP/JSON"
        eventService -> notificationService "Работа с расписанием уведомлений" "HTTP/JSON"
        eventService -> messageSubject "Отправка сообщений" "TCP/JSON"

        layoutDesignService -> layoutObjectStorage "Сохранение готовых макетов сообщений" "TCP"
        layoutDesignService -> layoutCache "Кэширование не готовых макетов сообщений" "TCP"

        notificationService -> notificationSubject "Отправка уведомлений пользователям" "TCP"
        notificationService -> notificationCache "Кэширование расписания" "TCP/JSON"

        messageSubject -> mailService "Получение сообщений" "TCP/JSON"
        messageSubject -> appService "Получение сообщений" "TCP/JSON"
        notificationSubject -> mailService "Получение уведомлений" "TCP/JSON"
        notificationSubject -> appService "Получение уведомлений" "TCP/JSON"
        
        mailService -> mailServers "Работа с почтовыми серверами пользователей" "SMTP"
        appService -> appCache "Кэширование сообщений для выдачи клиентскому приложению" "TCP/JSON"

        appService -> appClients "Работа с клиентскими приложениями пользователей" "HTTP/JSON"
    }

    views {
        systemContext eventSystem "ContextView" {
            include *
            autolayout lr
        }

        container eventSystem "ContainerView" {
            include *
            autolayout lr
        }
        
        dynamic eventSystem "CreatingEventUsecase" {
            eventManager -> gateway "Организатор мероприятия отправляет POST-запрос для создания мероприятия"
            gateway -> accountService "Прокси отправляет GET-запрос на сервис аккаунтов"
            accountService -> accountDb "Сервис аккаунтов проверяет права пользователя и статус подписки"
            gateway -> eventService "Прокси отправляет POST-запрос на сервис мероприятий"
            eventService -> layoutDesignService "Сервис мероприятий отправляет GET-запрос в сервис макетов на получение макета"
            layoutDesignService -> layoutObjectStorage "Сервис макетов получает макет из объектного хранилища макетов"
            eventService -> notificationService "Сервис мероприятий отправляет POST-запрос в сервис уведомлений на создание расписания мероприятия"
            eventService -> eventDb "Сервис мероприятий выполняет insert запрос в базу мероприятий"
            eventService -> eventObjectStorage "Сервис мероприятий выполняет сохраниение данных в объектном хранилище мероприятий"
            eventService -> messageSubject "Сервис мероприятий отправляет в очередь сообщений данные для рассылки"
            messageSubject -> mailService "Очередь сообщений доставляет информацию по мероприятию в сервис почтовой рассылки"
            messageSubject -> appService "Очередь сообщений доставляет информацию по мероприятию в сервис рассылки сообщений в приложения"
            mailService -> mailServers "Сервис почтовой рассылки отправляет сообщения на почтовые сервера пользователей по протоколу SMTP"
            appService -> appCache "Сервис рассылки сообщений в приложения кэширует сообщение для выдачи клиенту"
        }

        styles {
            element "Database" {
                shape Cylinder
                background #1168bd
                color #ffffff
            }

            element "Broker" {
                shape Pipe
                background #d35400
                color #ffffff
            }

            element "Container" {
                background #438dd5
                color #ffffff
            }

            element "Person" {
                shape Person
                background #08427b
                color #ffffff
            }
        }
    }
}