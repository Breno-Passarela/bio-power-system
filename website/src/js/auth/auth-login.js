document.getElementById("auth-login-button").addEventListener('click', () => {
    localStorage.setItem('token', generateToken());
});