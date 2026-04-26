const dbName = "conference_db";
const appDb = db.getSiblingDB(dbName);

appDb.users.drop();
appDb.talks.drop();
appDb.conferences.drop();
appDb.counters.drop();

appDb.createCollection("users");
appDb.createCollection("talks");
appDb.createCollection("conferences");

const users = [
  { id: NumberLong(1), email: "ivan1@mail.ru", name: "Ivan", surname: "Pavlov", phone: "+79990000001", password_hash: "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4" }, // hash of 1234
  { id: NumberLong(2), email: "olga2@mail.ru", name: "Olga", surname: "Petrova", phone: "+79990000002", password_hash: "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4" }, // hash of 1234
  { id: NumberLong(3), email: "petr3@mail.ru", name: "Petr", surname: "Sidorov", phone: "+79990000003", password_hash: "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4" }, // hash of 1234
  { id: NumberLong(4), email: "anna4@mail.ru", name: "Anna", surname: "Smirnova", phone: "+79990000004", password_hash: "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4" }, // hash of 1234
  { id: NumberLong(5), email: "dmitry5@mail.ru", name: "Dmitry", surname: "Kozlov", phone: "+79990000005", password_hash: "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4" }, // hash of 1234
  { id: NumberLong(6), email: "maria6@mail.ru", name: "Maria", surname: "Ivanova", phone: "+79990000006", password_hash: "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4" }, // hash of 1234
  { id: NumberLong(7), email: "nikita7@mail.ru", name: "Nikita", surname: "Morozov", phone: "+79990000007", password_hash: "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4" }, // hash of 1234
  { id: NumberLong(8), email: "elena8@mail.ru", name: "Elena", surname: "Orlova", phone: "+79990000008", password_hash: "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4" }, // hash of 1234
  { id: NumberLong(9), email: "sergey9@mail.ru", name: "Sergey", surname: "Volkov", phone: "+79990000009", password_hash: "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4" }, // hash of 1234
  { id: NumberLong(10), email: "irina10@mail.ru", name: "Irina", surname: "Fedorova", phone: "+79990000010", password_hash: "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4" } // hash of 1234
];

const conferences = [
  { id: NumberLong(1), title: "C++ Moscow", private_title: null, description: "Conference about modern C++ and architecture", paid_entrance: false, event_type: "public", registration: true, place: "Moscow", start_time: ISODate("2026-05-10T06:00:00Z"), end_time: ISODate("2026-05-10T16:00:00Z"), user_id: NumberLong(1) },
  { id: NumberLong(2), title: "Backend Days", private_title: null, description: "Backend technologies and performance engineering", paid_entrance: true, event_type: "public", registration: true, place: "Saint Petersburg", start_time: ISODate("2026-05-11T07:00:00Z"), end_time: ISODate("2026-05-11T15:00:00Z"), user_id: NumberLong(2) },
  { id: NumberLong(3), title: "Data Summit", private_title: "Internal DS", description: "Data engineering and analytics conference", paid_entrance: false, event_type: "private", registration: true, place: "Kazan", start_time: ISODate("2026-05-12T06:00:00Z"), end_time: ISODate("2026-05-12T15:00:00Z"), user_id: NumberLong(3) },
  { id: NumberLong(4), title: "AI Conf", private_title: null, description: "Machine learning production systems", paid_entrance: true, event_type: "public", registration: true, place: "Sochi", start_time: ISODate("2026-05-13T07:00:00Z"), end_time: ISODate("2026-05-13T16:00:00Z"), user_id: NumberLong(4) },
  { id: NumberLong(5), title: "DevOps Pro", private_title: null, description: "CI/CD, SRE and observability", paid_entrance: false, event_type: "public", registration: true, place: "Yekaterinburg", start_time: ISODate("2026-05-14T06:00:00Z"), end_time: ISODate("2026-05-14T15:00:00Z"), user_id: NumberLong(5) },
  { id: NumberLong(6), title: "Cloud Native RU", private_title: null, description: "Kubernetes and cloud-native ecosystem", paid_entrance: false, event_type: "public", registration: true, place: "Novosibirsk", start_time: ISODate("2026-05-15T06:00:00Z"), end_time: ISODate("2026-05-15T15:00:00Z"), user_id: NumberLong(6) },
  { id: NumberLong(7), title: "Mobile Future", private_title: null, description: "Mobile architecture and product metrics", paid_entrance: true, event_type: "public", registration: true, place: "Nizhny Novgorod", start_time: ISODate("2026-05-16T07:00:00Z"), end_time: ISODate("2026-05-16T15:00:00Z"), user_id: NumberLong(7) },
  { id: NumberLong(8), title: "Security Meetup", private_title: "Sec Internal", description: "Application security and threat modeling", paid_entrance: false, event_type: "private", registration: true, place: "Tomsk", start_time: ISODate("2026-05-17T07:00:00Z"), end_time: ISODate("2026-05-17T14:00:00Z"), user_id: NumberLong(8) },
  { id: NumberLong(9), title: "Frontend Forum", private_title: null, description: "Frontend platform and performance", paid_entrance: false, event_type: "public", registration: true, place: "Samara", start_time: ISODate("2026-05-18T07:00:00Z"), end_time: ISODate("2026-05-18T15:00:00Z"), user_id: NumberLong(9) },
  { id: NumberLong(10), title: "System Design Day", private_title: null, description: "Highload architecture and distributed systems", paid_entrance: true, event_type: "public", registration: true, place: "Moscow", start_time: ISODate("2026-05-19T06:00:00Z"), end_time: ISODate("2026-05-19T16:00:00Z"), user_id: NumberLong(10) }
];

const talks = [
  { id: NumberLong(1), title: "DDD in Practice", description: "Applying domain-driven design in services", start_time: ISODate("2026-05-10T07:00:00Z"), end_time: ISODate("2026-05-10T07:45:00Z"), user_id: NumberLong(1), event_id: NumberLong(1) },
  { id: NumberLong(2), title: "MongoDB Indexes", description: "Effective indexes for read-heavy APIs", start_time: ISODate("2026-05-11T08:00:00Z"), end_time: ISODate("2026-05-11T08:40:00Z"), user_id: NumberLong(2), event_id: NumberLong(2) },
  { id: NumberLong(3), title: "Kafka Pipelines", description: "Building resilient event pipelines", start_time: ISODate("2026-05-12T09:00:00Z"), end_time: ISODate("2026-05-12T09:45:00Z"), user_id: NumberLong(3), event_id: NumberLong(3) },
  { id: NumberLong(4), title: "MLOps Basics", description: "Model lifecycle and deployment strategy", start_time: ISODate("2026-05-13T09:00:00Z"), end_time: ISODate("2026-05-13T09:50:00Z"), user_id: NumberLong(4), event_id: NumberLong(4) },
  { id: NumberLong(5), title: "Observability", description: "Metrics, logs and traces in one platform", start_time: ISODate("2026-05-14T10:00:00Z"), end_time: ISODate("2026-05-14T10:45:00Z"), user_id: NumberLong(5), event_id: NumberLong(5) },
  { id: NumberLong(6), title: "K8s Security", description: "Secure defaults for cluster workloads", start_time: ISODate("2026-05-15T11:00:00Z"), end_time: ISODate("2026-05-15T11:45:00Z"), user_id: NumberLong(6), event_id: NumberLong(6) },
  { id: NumberLong(7), title: "Mobile Perf", description: "Performance budgets on mobile apps", start_time: ISODate("2026-05-16T12:00:00Z"), end_time: ISODate("2026-05-16T12:35:00Z"), user_id: NumberLong(7), event_id: NumberLong(7) },
  { id: NumberLong(8), title: "Threat Modeling", description: "Finding risks before implementation", start_time: ISODate("2026-05-17T09:00:00Z"), end_time: ISODate("2026-05-17T09:45:00Z"), user_id: NumberLong(8), event_id: NumberLong(8) },
  { id: NumberLong(9), title: "Web Core Vitals", description: "Optimization patterns for frontend apps", start_time: ISODate("2026-05-18T10:00:00Z"), end_time: ISODate("2026-05-18T10:40:00Z"), user_id: NumberLong(9), event_id: NumberLong(9) },
  { id: NumberLong(10), title: "Scaling APIs", description: "Scale read and write paths safely", start_time: ISODate("2026-05-19T12:00:00Z"), end_time: ISODate("2026-05-19T12:50:00Z"), user_id: NumberLong(10), event_id: NumberLong(10) }
];

appDb.users.insertMany(users);
appDb.conferences.insertMany(conferences);
appDb.talks.insertMany(talks);

appDb.users.createIndex({ email: 1 }, { unique: true, name: "idx_users_email" });
appDb.users.createIndex({ name: 1, surname: 1 }, { name: "idx_users_name_surname" });
appDb.conferences.createIndex({ user_id: 1 }, { name: "idx_events_user_id" });
appDb.conferences.createIndex({ start_time: 1 }, { name: "idx_events_start_time" });
appDb.talks.createIndex({ event_id: 1 }, { name: "idx_talks_event_id" });
appDb.talks.createIndex({ user_id: 1 }, { name: "idx_talks_user_id" });
appDb.talks.createIndex({ event_id: 1, start_time: 1, end_time: 1 }, { name: "idx_talks_event_time" });

appDb.counters.insertMany([
  { _id: "users", seq: NumberLong(10) },
  { _id: "events", seq: NumberLong(10) },
  { _id: "talks", seq: NumberLong(10) }
]);

print("Seed completed:");
print("users = " + appDb.users.countDocuments({}));
print("talks = " + appDb.talks.countDocuments({}));
print("conferences = " + appDb.conferences.countDocuments({}));
