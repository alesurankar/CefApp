// myServer/routes/commentRoute.js
const express = require("express");
const { isAuthenticatedUser } = require("../middlewares/user_actions/auth");
const { getUserComments, addComment } = require("../controllers/commentController");

const router = express.Router();

router.route("/comments")
      .get(isAuthenticatedUser, getUserComments)
      .post(isAuthenticatedUser, addComment);

module.exports = router;
