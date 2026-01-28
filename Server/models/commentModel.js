const mongoose = require("mongoose");

const commentSchema = new mongoose.Schema(
  {
    user: {
      type: Object,
      ref: "User", // references the User model
      required: true,
    },

    author: {
      type: String, // store the user's name for convenience
      required: true,
    },

    text: {
      type: String,
      required: [true, "Comment cannot be empty"],
      trim: true,
    },
    
    image: {
      type: String,
    },
  },
  {
    timestamps: true,
  }
);

module.exports = mongoose.model("Comment", commentSchema);