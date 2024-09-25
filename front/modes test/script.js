const themeToggle = document.getElementById('theme-toggle');
const themeStylesheet = document.getElementById('theme-stylesheet');
const savedTheme = localStorage.getItem('theme');

if (savedTheme) {
    themeStylesheet.setAttribute('href', savedTheme);
}

themeToggle.addEventListener('click', () => {
    if (themeStylesheet.getAttribute('href') === 'light-mode.css') {
        themeStylesheet.setAttribute('href', 'dark-mode.css');
        localStorage.setItem('theme', 'dark-mode.css');
    } else {
        themeStylesheet.setAttribute('href', 'light-mode.css');
        localStorage.setItem('theme', 'light-mode.css');
    }
});

document.getElementById("change").addEventListener("click", () => location.href = "page 2.html")