class registerController {
    register(req, res) {
        res.render("register", { layout: false });
    }
}

module.exports = registerController;