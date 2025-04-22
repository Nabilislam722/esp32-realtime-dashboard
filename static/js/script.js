const socket = io(`http://${location.hostname}:5000`);

socket.on('connect', () => console.log('Socket.IO connected'));
socket.on('update_data', data => {
    document.querySelectorAll('.data-card')[0].querySelector('.data-value').innerHTML =
        `${data.temperature} <span class="unit">°C</span>`;
    document.querySelectorAll('.data-card')[1].querySelector('.data-value').innerHTML =
        `${data.voltage} <span class="unit">V</span>`;
    document.querySelectorAll('.data-card')[2].querySelector('.data-value').innerHTML =
        `${data.amperage} <span class="unit">A</span>`;
});
socket.on('disconnect', () => console.warn('Socket.IO disconnected'));