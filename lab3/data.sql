INSERT INTO users (email, name, surname, phone, password_hash) VALUES
('ivan1@mail.ru', 'Ivan', 'Pavlov', '+79990000001', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4'),  -- hash of 1234
('olga2@mail.ru', 'Olga', 'Petrova', '+79990000002', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4'),  -- hash of 1234
('petr3@mail.ru', 'Petr', 'Sidorov', '+79990000003', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4'),  -- hash of 1234
('anna4@mail.ru', 'Anna', 'Smirnova', '+79990000004', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4'),  -- hash of 1234
('dmitry5@mail.ru', 'Dmitry', 'Kozlov', '+79990000005', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4'),  -- hash of 1234
('maria6@mail.ru', 'Maria', 'Ivanova', '+79990000006', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4'),  -- hash of 1234
('nikita7@mail.ru', 'Nikita', 'Morozov', '+79990000007', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4'),  -- hash of 1234
('elena8@mail.ru', 'Elena', 'Orlova', '+79990000008', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4'),  -- hash of 1234
('sergey9@mail.ru', 'Sergey', 'Volkov', '+79990000009', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4'),  -- hash of 1234
('irina10@mail.ru', 'Irina', 'Fedorova', '+79990000010', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4');  -- hash of 1234

INSERT INTO events (title, private_title, description, paid_entrance, event_type, registration, place, start_time, end_time, user_id) VALUES
('C++ Moscow', NULL, 'Conference about modern C++ and architecture', FALSE, 'public', TRUE, 'Moscow', '2026-05-10 09:00:00+03', '2026-05-10 19:00:00+03', 1),
('Backend Days', NULL, 'Backend technologies and performance engineering', TRUE, 'public', TRUE, 'Saint Petersburg', '2026-05-11 10:00:00+03', '2026-05-11 18:00:00+03', 2),
('Data Summit', 'Internal DS', 'Data engineering and analytics conference', FALSE, 'private', TRUE, 'Kazan', '2026-05-12 09:00:00+03', '2026-05-12 18:00:00+03', 3),
('AI Conf', NULL, 'Machine learning production systems', TRUE, 'public', TRUE, 'Sochi', '2026-05-13 10:00:00+03', '2026-05-13 19:00:00+03', 4),
('DevOps Pro', NULL, 'CI/CD, SRE, observability and platform teams', FALSE, 'public', TRUE, 'Yekaterinburg', '2026-05-14 09:00:00+03', '2026-05-14 18:00:00+03', 5),
('Cloud Native RU', NULL, 'Kubernetes and cloud-native ecosystem', FALSE, 'public', TRUE, 'Novosibirsk', '2026-05-15 09:00:00+03', '2026-05-15 18:00:00+03', 6),
('Mobile Future', NULL, 'Mobile architecture and product metrics', TRUE, 'public', TRUE, 'Nizhny Novgorod', '2026-05-16 10:00:00+03', '2026-05-16 18:00:00+03', 7),
('Security Meetup', 'Sec Internal', 'Application security and threat modeling', FALSE, 'private', TRUE, 'Tomsk', '2026-05-17 10:00:00+03', '2026-05-17 17:00:00+03', 8),
('Frontend Forum', NULL, 'Frontend platform and performance', FALSE, 'public', TRUE, 'Samara', '2026-05-18 10:00:00+03', '2026-05-18 18:00:00+03', 9),
('System Design Day', NULL, 'Highload architecture and distributed systems', TRUE, 'public', TRUE, 'Moscow', '2026-05-19 09:00:00+03', '2026-05-19 19:00:00+03', 10);

INSERT INTO talks (title, description, start_time, end_time, user_id, event_id) VALUES
('DDD in Practice', 'Applying domain-driven design in services', '2026-05-10 10:00:00+03', '2026-05-10 10:45:00+03', 1, 1),
('PostgreSQL Indexes', 'How B-tree and GIN indexes affect performance', '2026-05-11 11:00:00+03', '2026-05-11 11:45:00+03', 2, 2),
('Kafka Pipelines', 'Building resilient event pipelines', '2026-05-12 12:00:00+03', '2026-05-12 12:45:00+03', 3, 3),
('MLOps Basics', 'Model lifecycle and deployment strategy', '2026-05-13 12:00:00+03', '2026-05-13 12:45:00+03', 4, 4),
('Observability', 'Metrics, logs and traces in one platform', '2026-05-14 13:00:00+03', '2026-05-14 13:45:00+03', 5, 5),
('K8s Security', 'Secure defaults for cluster workloads', '2026-05-15 14:00:00+03', '2026-05-15 14:45:00+03', 6, 6),
('Mobile Perf', 'Performance budgets on mobile apps', '2026-05-16 15:00:00+03', '2026-05-16 15:45:00+03', 7, 7),
('Threat Modeling', 'Finding risks before implementation', '2026-05-17 11:00:00+03', '2026-05-17 11:45:00+03', 8, 8),
('Web Core Vitals', 'Optimization patterns for frontend apps', '2026-05-18 16:00:00+03', '2026-05-18 16:45:00+03', 9, 9),
('Scaling APIs', 'Scale read and write paths safely', '2026-05-19 17:00:00+03', '2026-05-19 17:45:00+03', 10, 10);
