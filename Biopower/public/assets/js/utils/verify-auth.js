function verificationAuth(display) {
    let captureToken = localStorage.getItem('token');

    if (!captureToken && display == 'home') window.location.href = "./src/pages/login.html";
}
