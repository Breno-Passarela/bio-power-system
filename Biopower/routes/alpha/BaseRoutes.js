class BaseRoutes {
    #router;

    constructor(router) {
        this.#router = router;
        this.validate();
    }

    validate() {
        if (!this.#router) {
            throw new Error("Router dependency not provided");
        }
    }

    get router() {
        return this.#router;
    }

    routeGet(endpoint, controller) {
        this.#router.get(endpoint, controller);
    }

    routePost(endpoint, controller) {
        this.#router.post(endpoint, controller);
    }

    routeDelete(endpoint, controller) {
        this.#router.delete(endpoint, controller);
    }

    routePut(endpoint, controller) {
        this.#router.put(endpoint, controller);
    }
}

module.exports = BaseRoutes;