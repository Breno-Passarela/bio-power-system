const BaseRoutes = require("./BaseRoutes");

class LoginRoutes extends BaseRoutes {
    constructor(router, controller) {
        super(router);
        this.controller = controller;
    }

    init() {
        this.routeGet("/", this.controller.login.bind(this.controller));
    }
}

module.exports = LoginRoutes;