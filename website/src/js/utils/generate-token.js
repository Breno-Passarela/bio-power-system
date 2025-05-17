function generateToken() {
    let token = '';
    let date = new Date();

    for(let i = 0; i < 10; i++) {
        token += Math.random().toString(36).substr(2, 10) + date.getTime();
    }

    return token;
}