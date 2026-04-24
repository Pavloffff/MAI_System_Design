CREATE TABLE IF NOT EXISTS users (
    id BIGSERIAL PRIMARY KEY,
    email TEXT NOT NULL UNIQUE CHECK (position('@' IN email) > 1),
    name TEXT NOT NULL CHECK (char_length(name) BETWEEN 1 AND 100),
    surname TEXT NOT NULL CHECK (char_length(surname) BETWEEN 1 AND 100),
    phone TEXT NOT NULL UNIQUE CHECK (phone ~ '^\+[0-9]{7,15}$'),
    password_hash TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS events (
    id BIGSERIAL PRIMARY KEY,
    title TEXT NOT NULL CHECK (char_length(title) BETWEEN 3 AND 200),
    private_title TEXT NULL,
    description TEXT NOT NULL CHECK (char_length(description) BETWEEN 10 AND 5000),
    paid_entrance BOOLEAN NOT NULL DEFAULT FALSE,
    event_type TEXT NOT NULL CHECK (event_type IN ('public', 'private')),
    registration BOOLEAN NOT NULL DEFAULT TRUE,
    place TEXT NOT NULL CHECK (char_length(place) BETWEEN 2 AND 255),
    start_time TIMESTAMPTZ NOT NULL,
    end_time TIMESTAMPTZ NOT NULL,
    user_id BIGINT NOT NULL REFERENCES users (id) ON DELETE RESTRICT,
    CHECK (end_time > start_time)
);

CREATE TABLE IF NOT EXISTS talks (
    id BIGSERIAL PRIMARY KEY,
    title TEXT NOT NULL CHECK (char_length(title) BETWEEN 3 AND 200),
    description TEXT NULL,
    start_time TIMESTAMPTZ NOT NULL,
    end_time TIMESTAMPTZ NOT NULL,
    user_id BIGINT NOT NULL REFERENCES users (id) ON DELETE RESTRICT,
    event_id BIGINT NOT NULL REFERENCES events (id) ON DELETE RESTRICT,
    CHECK (end_time > start_time)
);

CREATE INDEX IF NOT EXISTS idx_users_email ON users (email);
CREATE INDEX IF NOT EXISTS idx_users_name_surname ON users (name, surname);
CREATE INDEX IF NOT EXISTS idx_events_user_id ON events (user_id);
CREATE INDEX IF NOT EXISTS idx_events_start_time ON events (start_time);
CREATE INDEX IF NOT EXISTS idx_talks_event_id ON talks (event_id);
CREATE INDEX IF NOT EXISTS idx_talks_user_id ON talks (user_id);
CREATE INDEX IF NOT EXISTS idx_talks_event_time ON talks (event_id, start_time, end_time);
