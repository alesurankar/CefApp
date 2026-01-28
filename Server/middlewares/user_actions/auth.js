const jwt = require('jsonwebtoken');
const User = require('../../models/userModel');
const ErrorHandler = require('../../utils/errorHandler');
const asyncErrorHandler = require('../helpers/asyncErrorHandler');


exports.isAuthenticatedUser = asyncErrorHandler(async (req, res, next) => {
    // //  DEV-ONLY AUTH BYPASS
    // if (
    //     process.env.NODE_ENV === "development" &&
    //     process.env.SKIP_AUTH === "true"
    // ) {
    //     req.user = {
    //         _id: "64f000000000000000000001",
    //         name: "Dev User",
    //         role: "admin",
    //     };
    //     return next();
    // }

    // NORMAL AUTH FLOW (PRODUCTION)
    const { token } = req.cookies;

    if (!token) {
        return next(new ErrorHandler("Please Login to Access", 401))
    }

    const decodedData = jwt.verify(token, process.env.JWT_SECRET);
    req.user = await User.findById(decodedData.id);
    next();
});

exports.authorizeRoles = (...roles) => {
    return (req, res, next) => {

        if (!roles.includes(req.user.role)) {
            return next(new ErrorHandler(`Role: ${req.user.role} is not allowed`, 403));
        }
        next();
    }
}