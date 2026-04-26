# Домашнее задание 04

## Документно-ориентированная база данных MongoDB

Вариант №3: сайт конференции (MongoDB + userver)

### Выполнил студент группы М8О-106СВ-25 Павлов Иван Дмитриевич

## 1. Проектирование документной модели

Для системы выделены коллекции:

- `users`
- `talks`
- `conferences`

Полное описание структуры документов и обоснование выбора embedded/references:

- [schema_design.md](schema_design.md)

## 2. Создание базы данных и коллекций

- Используется официальный образ `mongo:7.0` в [docker-compose.yaml](docker-compose.yaml);
- Инициализация выполняется скриптом [init-mongo.js](init-mongo.js);
- Тестовые данные находятся в [data.js](data.js) (минимум 10 документов в каждой коллекции);
- Присутствуют типы данных: `String`, `Boolean`, `Date`, `ObjectId`, `null`.

## 3. CRUD операции

MongoDB-запросы для всех операций по варианту (и дополнительные примеры операторов):

- [queries.js](queries.js)

Реализованы:

- создание нового пользователя;
- поиск пользователя по логину;
- поиск пользователя по маске имени и фамилии;
- создание доклада;
- получение списка всех докладов;
- добавление доклада в конференцию;
- получение списка докладов конференции;
- обновления и удаления документов;
- операторы `$eq`, `$ne`, `$gt`, `$lt`, `$in`, `$and`, `$or`, `$push`, `$pull`, `$addToSet`.

## 4. Валидация схем

Скрипт [validation.js](validation.js) содержит:

- валидацию `users` через `$jsonSchema`;
- обязательные поля (`required`);
- типы данных (`bsonType`);
- ограничения (`minLength`, `maxLength`, `pattern`, `enum`, `minItems`);
- тест вставки невалидных документов (ожидаемые ошибки).

## 5. Агрегация

В `queries.js` добавлен aggregation pipeline:

- `$match` -> `$group` -> `$lookup` -> `$unwind` -> `$project` -> `$sort`

Запрос считает количество докладов по конференциям и среднюю длительность.

## 6. Подключение API к MongoDB

Репозитории реализованы в слое `src/infrastructure/mongo`:

- `MongoUserRepository`
- `MongoTalkRepository`
- `MongoEventRepository`

Что сделано в коде:

- компоненты `UserRepositoryComponent`, `TalkRepositoryComponent`, `EventRepositoryComponent` создают Mongo-репозитории и берут URI из переменной окружения `MONGO_URI` (задается в `docker-compose.yaml`);
- в `main.cpp` используется тот же набор application/handler-компонентов, DI подключает реализацию репозиториев через инфраструктурные компоненты;
- для генерации доменных идентификаторов (`id` типа `int64`) используется коллекция `counters` (аналог sequence), чтобы API остался совместим с контрактом `lab3`;
- в `Dockerfile` добавлены пакеты `libmongocxx-dev` и `libbsoncxx-dev`, в `CMakeLists.txt` подключены `mongo::mongocxx_shared` и `mongo::bsoncxx_shared`.

## 7. Результат

- `schema_design.md` - [schema_design.md](schema_design.md)
- `data.js` - [data.js](data.js)
- `queries.js` - [queries.js](queries.js)
- `validation.js` - [validation.js](validation.js)
- `README.md` - [README.md](README.md)
- Dockerfile - [Dockerfile](Dockerfile), docker-compose.yaml - [docker-compose.yaml](docker-compose.yaml)

## 8. Запуск

```bash
docker compose up --build
```

Проверка количества документов:

```bash
docker exec -it lab4-mongo mongosh -u mongo -p mongo --authenticationDatabase admin --eval "db.getSiblingDB('conference_db').users.countDocuments()"
docker exec -it lab4-mongo mongosh -u mongo -p mongo --authenticationDatabase admin --eval "db.getSiblingDB('conference_db').talks.countDocuments()"
docker exec -it lab4-mongo mongosh -u mongo -p mongo --authenticationDatabase admin --eval "db.getSiblingDB('conference_db').conferences.countDocuments()"
```
