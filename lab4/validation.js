const dbName = "conference_db";
const appDb = db.getSiblingDB(dbName);

const userValidator = {
  $jsonSchema: {
    bsonType: "object",
    required: ["email", "name", "surname", "phone", "password_hash"],
    additionalProperties: true,
    properties: {
      email: {
        bsonType: "string",
        pattern: "^[^\\s@]+@[^\\s@]+\\.[^\\s@]+$",
        description: "must be valid email"
      },
      name: {
        bsonType: "string",
        minLength: 1,
        maxLength: 100
      },
      surname: {
        bsonType: "string",
        minLength: 1,
        maxLength: 100
      },
      phone: {
        bsonType: "string",
        pattern: "^\\+\\d{7,15}$"
      },
      password_hash: { bsonType: "string" }
    }
  }
};

const usersExists = appDb.getCollectionInfos({ name: "users" }).length > 0;

if (!usersExists) {
  appDb.createCollection("users", { validator: userValidator, validationLevel: "strict" });
} else {
  appDb.runCommand({
    collMod: "users",
    validator: userValidator,
    validationLevel: "strict",
    validationAction: "error"
  });
}

print("Validation configured for users collection");

