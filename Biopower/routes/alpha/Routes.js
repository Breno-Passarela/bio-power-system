const express = require("express");

const LoginController = require('../controllers/loginController');
const LoginRoutes = require("./LoginRoutes");

class Routes {
    static init(app) {
        const router = express.Router();

        const loginController = new LoginController();

        const loginRoutes = new LoginRoutes(router, loginController);

        loginRoutes.init();
        userRoutes.init();

        app.use("/login", router);
    }
}

module.exports = Routes;