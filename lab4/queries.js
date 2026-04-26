const dbName = "conference_db";
const appDb = db.getSiblingDB(dbName);

// 1) Create new user
const nextUserId = NumberLong(appDb.counters.findOneAndUpdate(
  { _id: "users" },
  { $inc: { seq: NumberLong(1) } },
  { returnDocument: "after" }
).seq);
appDb.users.insertOne({
  id: nextUserId,
  email: "new.user@mail.ru",
  name: "New",
  surname: "User",
  phone: "+79995550000",
  password_hash: "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4" // hash of 1234
});

// 2) Find user by login/email ($eq)
appDb.users.findOne(
  { email: { $eq: "ivan1@mail.ru" } },
  { projection: { password_hash: 0 } }
);

// 3) Find users by name/surname mask (regex + $and + $ne)
appDb.users
  .find({
    $and: [
      { name: { $regex: "^Iv", $options: "i" } },
      { surname: { $regex: "^Pa", $options: "i" } },
      { phone: { $ne: "" } }
    ]
  })
  .sort({ name: 1, surname: 1 });

// 4) Create talk
const speaker = appDb.users.findOne({ email: "olga2@mail.ru" });
const conference = appDb.conferences.findOne({ title: "Backend Days" });
const nextTalkId = NumberLong(appDb.counters.findOneAndUpdate(
  { _id: "talks" },
  { $inc: { seq: NumberLong(1) } },
  { returnDocument: "after" }
).seq);

appDb.talks.insertOne({
  id: nextTalkId,
  title: "Caching Strategies",
  description: "Cache invalidation in distributed systems",
  start_time: ISODate("2026-05-11T12:00:00Z"),
  end_time: ISODate("2026-05-11T12:45:00Z"),
  user_id: speaker.id,
  event_id: conference.id
});

// 5) Get all talks
appDb.talks.find({}).sort({ start_time: 1 });

// 6) Add talk to conference (update talks.event_id)
const targetConference = appDb.conferences.findOne({ title: "System Design Day" });
appDb.talks.updateOne(
  { id: nextTalkId },
  { $set: { event_id: targetConference.id } }
);

// 7) Get talks of conference
appDb.talks
  .find(
    { event_id: targetConference.id },
    { projection: { title: 1, description: 1, start_time: 1, end_time: 1, user_id: 1, event_id: 1 } }
  )
  .sort({ start_time: 1 });

// Additional reads with operators from assignment
appDb.talks.find({
  $or: [{ start_time: { $gt: ISODate("2026-05-15T00:00:00Z") } }, { title: { $in: ["DDD in Practice", "Scaling APIs"] } }]
});

appDb.users.find({
  $and: [
    { email: { $ne: "none@mail.ru" } },
    { name: { $in: ["Ivan", "Olga", "Irina"] } }
  ]
});

// Update examples
appDb.users.updateOne(
  { email: "new.user@mail.ru" },
  {
    $set: { surname: "Updated" }
  }
);

appDb.talks.updateOne(
  { id: nextTalkId },
  {
    $set: { description: "Updated talk description" }
  }
);

// Array operators example for assignment
if (appDb.getCollectionInfos({ name: "query_examples" }).length === 0) {
  appDb.createCollection("query_examples");
}
appDb.query_examples.deleteMany({});
appDb.query_examples.insertOne({ _id: 1, values: [1, 2, 3] });
appDb.query_examples.updateOne({ _id: 1 }, { $push: { values: 4 } });
appDb.query_examples.updateOne({ _id: 1 }, { $addToSet: { values: 4 } });
appDb.query_examples.updateOne({ _id: 1 }, { $pull: { values: 2 } });

// Delete examples
appDb.talks.deleteOne({ title: "Caching Strategies" });
appDb.users.deleteOne({ email: "new.user@mail.ru" });

// Optional aggregation pipeline: number of talks per conference
appDb.talks.aggregate([
  { $match: { start_time: { $gt: ISODate("2026-05-10T00:00:00Z") } } },
  { $group: { _id: "$event_id", talksCount: { $sum: 1 } } },
  {
    $lookup: {
      from: "conferences",
      localField: "_id",
      foreignField: "id",
      as: "conference"
    }
  },
  { $unwind: "$conference" },
  {
    $project: {
      _id: 0,
      event_id: "$_id",
      conference_title: "$conference.title",
      talksCount: 1
    }
  },
  { $sort: { talksCount: -1, conference_title: 1 } }
]);
