const mongoose = require('mongoose');
const MONGO_URI = process.env.MONGO_URI;

const connectDatabase = () => {
    mongoose.connect(MONGO_URI)
        .then(() => {
            console.log("Mongoose Connected");
        })
        .catch((err) => {
            console.error("Mongoose connection error:", err);
        });
}

module.exports = connectDatabase;