# Оптимизация SQL-запросов

## EXPLAIN до и после

### 1. Поиск пользователя по email
До:
```sql
EXPLAIN SELECT * FROM users WHERE email = 'ivan1@mail.ru';
-- Seq Scan on users  (cost=0.00..16.15 rows=1 width=168)
--   Filter: ((name = 'Ivan'::text) AND (surname = 'Pavlov'::text))
```

После:
```sql
EXPLAIN SELECT * FROM users WHERE email = 'ivan1@mail.ru';
-- Index Scan using idx_users_email on users  (cost=0.15..8.17 rows=1 width=168)
--   Index Cond: (email = 'ivan1@mail.ru'::text)
```

### 2. Список докладов в конференции
До:
```sql
EXPLAIN SELECT * FROM talks WHERE event_id = 10 ORDER BY start_time;
-- Sort  (cost=17.65..17.66 rows=3 width=104)
--   Sort Key: start_time
--   ->  Seq Scan on talks  (cost=0.00..17.62 rows=3 width=104)
--         Filter: (event_id = 10)
```

После:
```sql
EXPLAIN SELECT * FROM talks WHERE event_id = 10 ORDER BY start_time;
-- Sort  (cost=11.31..11.31 rows=3 width=104)
--   Sort Key: start_time
--   ->  Bitmap Heap Scan on talks  (cost=4.17..11.28 rows=3 width=104)
--         Recheck Cond: (event_id = 10)
--         ->  Bitmap Index Scan on idx_talks_event_time  (cost=0.00..4.17 rows=3 width=0)
--               Index Cond: (event_id = 10)
```

### 3. Поиск пользователей по маске имени/фамилии
До:
```sql
EXPLAIN SELECT * FROM users WHERE name = 'Ivan' AND surname = 'Pavlov';
-- Seq Scan on users  (cost=0.00..16.15 rows=1 width=168)
--   Filter: ((name = 'Ivan'::text) AND (surname = 'Pavlov'::text))
```

После:
```sql
EXPLAIN SELECT * FROM users WHERE name = 'Ivan' AND surname = 'Pavlov';
-- Index Scan using idx_users_name_surname on users  (cost=0.15..8.17 rows=1 width=168)
--   Index Cond: ((name = 'Ivan'::text) AND (surname = 'Pavlov'::text))
```

## Вывод
После создания индексов планы выполнения уходят от полных сканов таблиц в пользу индексных операций, что уменьшает стоимость запроса и латентность на росте данных.
