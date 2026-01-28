/**
 * User Controller
 * Handles all user-related operations including authentication, profile management,
 * password reset, and admin user management for the PetShop application
 */

const User = require('../models/userModel');
const asyncErrorHandler = require('../middlewares/helpers/asyncErrorHandler');
const sendToken = require('../utils/sendToken');

/**
 * Register New User
 * @route POST /api/v1/register
 * @access Public
 */
exports.registerUser = asyncErrorHandler(async (req, res, next) => {
    console.log("🔥 registerUser triggered");

    const { name, email, password } = req.body;

    const existingUser = await User.findOne({ email });
    if (existingUser) {
        return res.status(400).json({ message: "User already exists" });
    }

    const user = await User.create ({
        name,
        email,     
        password,
    });
    sendToken(user, 201, res);
});



/**
 * User Login
 * @route POST /api/v1/login
 * @access Public
 */
exports.loginUser = asyncErrorHandler(async (req, res, next) => {
    console.log("🔥 loginUser triggered");

    const { email, password } = req.body;
    
    const user = await User.findOne({ email }).select("+password");
    if (!user) {
        return res.status(401).json({ message: "Invalid email or password" });
    }

    const isPasswordMatched = await user.comparePassword(password);
    if (!isPasswordMatched) {
        return res.status(401).json({ message: "Invalid email or password" });
    }

    sendToken(user, 200, res);
});

/**
 * User Logout
 * Clears the authentication token cookie
 * @route POST /api/v1/logout
 * @access Private
 */
exports.logoutUser = asyncErrorHandler(async (req, res, next) => {
    // Clear the token cookie by setting it to null with immediate expiry
    res.cookie("token", null, {
        expires: new Date(Date.now()),
        httpOnly: true,
    });

    res.status(200).json({
        success: true,
        message: "Logged Out",
    });
});

// Get User Details
exports.getUserDetails = asyncErrorHandler(async (req, res, next) => {
    res.status(200).json({
        success: true,
        user: req.user,
    });
});

// /**
//  * Forgot Password
//  * Generates password reset token and sends reset email to user
//  * @route POST /api/v1/password/forgot
//  * @access Public
//  */
// exports.forgotPassword = asyncErrorHandler(async (req, res, next) => {
//     // Find user by email
//     const user = await User.findOne({ email: req.body.email });

//     if (!user) {
//         return next(new ErrorHandler("User Not Found", 404));
//     }

//     // Generate password reset token
//     const resetToken = await user.getResetPasswordToken();

//     // Save user with reset token (skip validation)
//     await user.save({ validateBeforeSave: false });

//     // Create password reset URL (force HTTPS in production)
//     const resetPasswordUrl = `https://${req.get("host")}/password/reset/${resetToken}`;

//     try {
//         // Send password reset email using SendGrid template
//         await sendEmail({
//             email: user.email,
//             templateId: process.env.SENDGRID_RESET_TEMPLATEID,
//             data: {
//                 reset_url: resetPasswordUrl
//             }
//         });

//         res.status(200).json({
//             success: true,
//             message: `Email sent to ${user.email} successfully`,
//         });

//     } catch (error) {
//         // Clean up reset token if email sending fails
//         user.resetPasswordToken = undefined;
//         user.resetPasswordExpire = undefined;

//         await user.save({ validateBeforeSave: false });
//         return next(new ErrorHandler(error.message, 500))
//     }
// });

// // Reset Password
// exports.resetPassword = asyncErrorHandler(async (req, res, next) => {

//     // create hash token
//     const resetPasswordToken = crypto.createHash("sha256").update(req.params.token).digest("hex");

//     const user = await User.findOne({
//         resetPasswordToken,
//         resetPasswordExpire: { $gt: Date.now() }
//     });

//     if (!user) {
//         return next(new ErrorHandler("Invalid reset password token", 404));
//     }

//     user.password = req.body.password;
//     user.resetPasswordToken = undefined;
//     user.resetPasswordExpire = undefined;

//     await user.save();
//     sendToken(user, 200, res);
// });

// // Update Password
// exports.updatePassword = asyncErrorHandler(async (req, res, next) => {

//     const user = await User.findById(req.user.id).select("+password");

//     const isPasswordMatched = await user.comparePassword(req.body.oldPassword);

//     if (!isPasswordMatched) {
//         return next(new ErrorHandler("Old Password is Invalid", 400));
//     }

//     user.password = req.body.newPassword;
//     await user.save();
//     sendToken(user, 201, res);
// });

// // Update User Profile
// exports.updateProfile = asyncErrorHandler(async (req, res, next) => {

//     const newUserData = {
//         name: req.body.name,
//         email: req.body.email,
//     }

//     if (req.body.avatar !== "") {
//         const user = await User.findById(req.user.id);

//         const imageId = user.avatar.public_id;

//         await cloudinary.v2.uploader.destroy(imageId);

//         const myCloud = await cloudinary.v2.uploader.upload(req.body.avatar, {
//             folder: "avatars",
//             width: 150,
//             crop: "scale",
//         });

//         newUserData.avatar = {
//             public_id: myCloud.public_id,
//             url: myCloud.secure_url,
//         }
//     }

//     await User.findByIdAndUpdate(req.user.id, newUserData, {
//         new: true,
//         runValidators: true,
//         useFindAndModify: true,
//     });

//     res.status(200).json({
//         success: true,
//     });
// });

// // ADMIN DASHBOARD

// // Get All Users --ADMIN
// exports.getAllUsers = asyncErrorHandler(async (req, res, next) => {

//     const users = await User.find();

//     res.status(200).json({
//         success: true,
//         users,
//     });
// });

// // Get Single User Details --ADMIN
// exports.getSingleUser = asyncErrorHandler(async (req, res, next) => {

//     const user = await User.findById(req.params.id);

//     if (!user) {
//         return next(new ErrorHandler(`User doesn't exist with id: ${req.params.id}`, 404));
//     }

//     res.status(200).json({
//         success: true,
//         user,
//     });
// });

// // Update User Role --ADMIN
// exports.updateUserRole = asyncErrorHandler(async (req, res, next) => {

//     const newUserData = {
//         name: req.body.name,
//         email: req.body.email,
//         gender: req.body.gender,
//         role: req.body.role,
//     }

//     await User.findByIdAndUpdate(req.params.id, newUserData, {
//         new: true,
//         runValidators: true,
//         useFindAndModify: false,
//     });

//     res.status(200).json({
//         success: true,
//     });
// });

// // Delete Role --ADMIN
// exports.deleteUser = asyncErrorHandler(async (req, res, next) => {

//     const user = await User.findById(req.params.id);

//     if (!user) {
//         return next(new ErrorHandler(`User doesn't exist with id: ${req.params.id}`, 404));
//     }

//     await user.remove();

//     res.status(200).json({
//         success: true
//     });
// });