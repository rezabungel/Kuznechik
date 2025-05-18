async function convertStrToHex() {
    const dataStr = document.getElementById('strInput').value;
    const container = document.getElementById('strHexResultContainer');
    try {
        const response = await fetch(`/api/tools/str-to-hex?data_str=${encodeURIComponent(dataStr)}`);
        const result = await response.json();
        if (!response.ok) {
            let errorMsg = `Error ${response.status}: `;
            if (Array.isArray(result.detail)) {
                errorMsg += result.detail.map(err => err.msg).join(', ');
            } else {
                errorMsg += result.detail || 'Unknown error';
            }
            container.innerHTML = errorMsg;
        } else {
            container.innerHTML = `Hex: <span id="strHexResult">${result.data_hex}</span>`;
        }
    } catch (error) {
        container.innerHTML = error.message;
    }
}

async function convertHexToStr() {
    const dataHex = document.getElementById('hexInput').value;
    const container = document.getElementById('hexStrResultContainer');
    try {
        const response = await fetch(`/api/tools/hex-to-str?data_hex=${dataHex}`);
        const result = await response.json();
        if (!response.ok) {
            let errorMsg = `Error ${response.status}: `;
            if (Array.isArray(result.detail)) {
                errorMsg += result.detail.map(err => err.msg).join(', ');
            } else {
                errorMsg += result.detail || 'Unknown error';
            }
            container.innerHTML = errorMsg;
        } else {
            container.innerHTML = `String: <span id="hexStrResult">${result.data_str}</span>`;
        }
    } catch (error) {
        container.innerHTML = error.message;
    }
}

async function getHexInfo() {
    const dataHex = document.getElementById('hexInfoInput').value;
    const container = document.getElementById('hexInfoResultContainer');
    try {
        const response = await fetch(`/api/tools/hex-info?data_hex=${dataHex}`);
        const result = await response.json();
        if (!response.ok) {
            let errorMsg = `Error ${response.status}: `;
            if (Array.isArray(result.detail)) {
                errorMsg += result.detail.map(err => err.msg).join(', ');
            } else {
                errorMsg += result.detail || 'Unknown error';
            }
            container.innerHTML = errorMsg;
        } else {
            const output = `<br>
        Length in hex: ${result.len_hex}<br>
        Length in bytes: ${result.len_byte}<br>
        Length in bits: ${result.len_bit}`;
            container.innerHTML = `Info: <span id="hexInfoResult">${output}</span>`;
        }
    } catch (error) {
        container.innerHTML = error.message;
    }
}

async function encryptData() {
    const blk = document.getElementById('encryptInput').value;
    const key = document.getElementById('encryptKey').value;
    const container = document.getElementById('encryptResultContainer');
    try {
        const response = await fetch(`/api/kuznechik/encrypt?blk=${blk}&key=${key}`, { method: 'POST' });
        let resultText = await response.text();
        if (!response.ok) {
            let errorMsg = `Error ${response.status}: `;
            try {
                const errorObj = JSON.parse(resultText);
                if (Array.isArray(errorObj.detail)) {
                    errorMsg += errorObj.detail.map(err => err.msg).join(', ');
                } else {
                    errorMsg += errorObj.detail || 'Unknown error';
                }
            } catch (e) {
                errorMsg += resultText;
            }
            container.innerHTML = errorMsg;
        } else {
            if (resultText.startsWith('"') && resultText.endsWith('"')) {
                resultText = resultText.slice(1, -1);
            }
            container.innerHTML = `Encrypted: <span id="encryptResult">${resultText}</span>`;
        }
    } catch (error) {
        container.innerHTML = error.message;
    }
}

async function decryptData() {
    const blk = document.getElementById('decryptInput').value;
    const key = document.getElementById('decryptKey').value;
    const container = document.getElementById('decryptedResultContainer');
    try {
        const response = await fetch(`/api/kuznechik/decrypt?blk=${blk}&key=${key}`, { method: 'POST' });
        let resultText = await response.text();
        if (!response.ok) {
            let errorMsg = `Error ${response.status}: `;
            try {
                const errorObj = JSON.parse(resultText);
                if (Array.isArray(errorObj.detail)) {
                    errorMsg += errorObj.detail.map(err => err.msg).join(', ');
                } else {
                    errorMsg += errorObj.detail || 'Unknown error';
                }
            } catch (e) {
                errorMsg += resultText;
            }
            container.innerHTML = errorMsg;
        } else {
            if (resultText.startsWith('"') && resultText.endsWith('"')) {
                resultText = resultText.slice(1, -1);
            }
            container.innerHTML = `Decrypted: <span id="decryptedResult">${resultText}</span>`;
        }
    } catch (error) {
        container.innerHTML = error.message;
    }
}