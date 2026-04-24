-- 1) Create new user
INSERT INTO users (email, name, surname, phone, password_hash)
VALUES ('ivan1@mail.ru', 'Ivan', 'Pavlov', '+79991112233', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4') -- hash of 1234
RETURNING id, email, name, surname, phone;

-- 2) Find user by login (email)
SELECT id, email, name, surname, phone
FROM users
WHERE email = 'ivan1@mail.ru';

-- 3) Find users by name/surname mask
SELECT id, email, name, surname, phone
FROM users
WHERE name ILIKE 'Iv%' AND surname ILIKE 'Pa%'
ORDER BY id;

-- 4) Create talk
INSERT INTO talks (title, description, start_time, end_time, user_id, event_id)
VALUES ('New talk', 'Talk from SQL script', '2026-05-20 11:00:00+03', '2026-05-20 11:45:00+03', 1, 1)
RETURNING id, title, user_id, event_id;

-- 5) Get all talks
SELECT id, title, description, start_time, end_time, user_id, event_id
FROM talks
ORDER BY id;

-- 6) Add talk to conference
UPDATE talks
SET event_id = 2
WHERE id = 1
RETURNING id, title, event_id;

-- 7) Get talks of conference
SELECT t.id, t.title, t.description, t.start_time, t.end_time, t.user_id, t.event_id
FROM talks t
JOIN events e ON e.id = t.event_id
WHERE e.id = 2
ORDER BY t.start_time;
