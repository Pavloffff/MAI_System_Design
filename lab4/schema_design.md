# Проектирование документной модели (MongoDB)

Вариант №3: сайт конференции (пользователь, доклад, конференция).

## 1) Коллекции

- `users` — соответствует таблице `users`;
- `conferences` — соответствует таблице `events`;
- `talks` — соответствует таблице `talks`.

## 2) Структура документов

### Коллекция `users`

```json
{
  "_id": { "$oid": "..." },
  "email": "ivan1@mail.ru",
  "name": "Ivan",
  "surname": "Pavlov",
  "phone": "+79990000001",
  "password_hash": "03ac6742..."
}
```

### Коллекция `conferences` (аналог `events`)

```json
{
  "_id": { "$oid": "..." },
  "title": "System Design Day",
  "private_title": null,
  "description": "Highload architecture and distributed systems",
  "paid_entrance": true,
  "event_type": "public",
  "registration": true,
  "place": "Moscow",
  "start_time": { "$date": "2026-05-19T06:00:00Z" },
  "end_time": { "$date": "2026-05-19T16:00:00Z" },
  "user_id": { "$oid": "..." }
}
```

### Коллекция `talks`

```json
{
  "_id": { "$oid": "..." },
  "title": "Scaling APIs",
  "description": "Scale read and write paths safely",
  "start_time": { "$date": "2026-05-19T12:00:00Z" },
  "end_time": { "$date": "2026-05-19T12:50:00Z" },
  "user_id": { "$oid": "..." },
  "event_id": { "$oid": "..." }
}
```

## 3) Embedded vs references

В этой модели embedded-документы не используются, чтобы максимально повторить доменную структуру.

- `conferences.user_id -> users._id` (reference)
- `talks.user_id -> users._id` (reference)
- `talks.event_id -> conferences._id` (reference)

## 4) Обоснование

- Сущности раздельные и связаны по идентификаторам;
- API-операции варианта естественно строятся вокруг этих связей;
- При добавлении доклада в конференцию достаточно изменить `talks.event_id`, как в `lab3` (`UPDATE talks SET event_id = ...`).

## 5) Индексы

- `users.email` (unique) — поиск пользователя по логину/email;
- `users.name, users.surname` — поиск по маске имени/фамилии;
- `conferences.user_id` — выборки конференций пользователя;
- `conferences.start_time` — выборки/сортировка по времени;
- `talks.event_id` — получение списка докладов конференции;
- `talks.user_id` — выборки докладов автора;
- `talks.event_id, talks.start_time, talks.end_time` — сортировка докладов в конференции.
