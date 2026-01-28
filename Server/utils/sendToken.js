const sendToken = (user, statusCode, res) => {
    const token = user.getJWTToken();

    const options = {
        expires: new Date(
            Date.now() + (process.env.COOKIE_EXPIRE || 7) * 24 * 60 * 60 * 1000
        ),
        httpOnly: true,
        secure: process.env.NODE_ENV === 'production',
        sameSite: process.env.NODE_ENV === 'production' ? 'Strict' : 'Lax'
    }

    // Exclude password from response
    const { password, ...userData } = user.toObject();

    res.status(statusCode)
       .cookie('token', token, options)
       .json({
           success: true,
           user: userData,
           token, // optional if frontend uses cookie
       });
}

module.exports = sendToken;