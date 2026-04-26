const dbName = "conference_db";
const appDb = db.getSiblingDB(dbName);

print("Initializing MongoDB for lab4...");

// 1) Create schema validation first
load("/docker-entrypoint-initdb.d/validation.js");

// 2) Seed test data (recreates collections)
load("/docker-entrypoint-initdb.d/data.js");

// 3) Re-apply validation after recreate in data.js
load("/docker-entrypoint-initdb.d/validation.js");

print("MongoDB init completed for " + appDb.getName());
