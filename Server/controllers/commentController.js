const Comment = require("../models/commentModel");
const asyncErrorHandler = require("../middlewares/helpers/asyncErrorHandler");

/**
 * Add a new comment
 * @route POST /api/v1/comment
 * @access Private
 */
exports.addComment = asyncErrorHandler(async (req, res, next) => {
    const { text } = req.body;

    if (!text) {
        return res.status(400).json({ success: false, message: "Comment text is required" });
    }

    const comment = await Comment.create({
        text,
        user: req.user, // matches your schema
        author: req.user.name, // optional convenience
    });

    res.status(201).json({
        success: true,
        comment,
    });
});

/**
 * Get all comments by logged-in user
 * @route GET /api/v1/my-comments
 * @access Private
 */
exports.getUserComments = asyncErrorHandler(async (req, res, next) => {
    const comments = await Comment.find({ user: req.user._id }).sort({ createdAt: -1 });

    res.status(200).json({
        success: true,
        count: comments.length,
        comments,
    });
});






