# Домашнее задание 02

## Разработка REST API сервиса

### Вариант №3 — Сайт конференции (аналогичный https://www.eventboost.com/ru-RU/)

### Выполнил студент группы М8О-106СВ-25 Павлов Иван Дмитриевич

## 1. Описание выбранного варианта

Приложение должно содержать следующие данные:
- Пользователь
- Доклад
- Конференция
Реализовать API:
- Создание нового пользователя
- Поиск пользователя по логину
- Поиск пользователя по маске имя и фамилии
- Создание доклада
- Получение списка всех докладов
- Добавление доклада в конференцию
- Получение списка докладов в конференции

## 2. Проектирование REST API

В файле [api/openapi.yaml](api/openapi.yaml) схема API. В директории [docs/definitions](docs/definitions) - модели данных. 

---

## 3. Реализация REST API сервиса

- Реализовано на Userver;
- Реализованы все ручки из варианта + добавлены ручки на логин и на создание Конференции;
- Соблюдены принципы Domain Driven Design, имплементирован DI с помощью Userver Components;
- DTO сгенерировано chaotic.

---

## 4. Реализация аутентификации

- Реализована JWT авторизация (простая, HS256). Пристствует валидация юзера по id с помощью jwt на некоторых endpoint-ах, также на всех endpoint-ах, кроме Create User и login. Подробнее в [configs/static_config.yaml](configs/static_config.yaml) 

---

## 5. Документирование API

Openapi-спецификация в [api/openapi.yaml](api/openapi.yaml) 

---

## 6. Тестирование

Интеграционные тесты на python в директории tests

---

## 7. Результат

- Исходный код: [src](src) 
- openapi.yaml: 
- README.md:
- Тесты: 
- Dockerfile: 
- docker-compose.yaml: 

---

## 8. Запуск
```
git clone https://github.com/Pavloffff/MAI_System_Design.git
cd lab2
docker-compose up
```

## Сборка из vscode в devcontainer

1. Скачать репозиторий и открыть его в vscode из директории lab2:
```
git clone https://github.com/Pavloffff/MAI_System_Design.git
cd lab2
code .
```
2. Скачать расширение ms-vscode-remote.remote-containers
3. Открыть проект в vscode и нажать 'Reopen in container'
4. Открыть терминал от пользователя user (можно в vscode Terminal -> New Terminal либо через docker exec и sudo su user)
5. Собрать проект с помощью:
```sh
make build-debug
```
6. Прописать симлинку, чтобы в vscode не было ошибок
```sh
ln -sf build-debug/compile_commands.json .
```

## Запуск из devcontainer
```sh
make start-debug
```

## Тесты из devcontainer
```sh
make test-debug
```
