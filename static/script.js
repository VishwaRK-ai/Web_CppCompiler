// Handle Tab Key Indentation
document.getElementById('codeArea').addEventListener('keydown', function(e) {
    if (e.key == 'Tab') {
        e.preventDefault();
        var start = this.selectionStart;
        var end = this.selectionEnd;
        this.value = this.value.substring(0, start) + "    " + this.value.substring(end);
        this.selectionStart = this.selectionEnd = start + 4;
    }
});

// Run Code Function
async function runCode() {
    const code = document.getElementById("codeArea").value;
    const outputDiv = document.getElementById("output");
    const btn = document.getElementById("runBtn");

    outputDiv.innerText = "";
    btn.innerText = "Compiling...";
    btn.disabled = true;
    btn.style.backgroundColor = "#555";

    try {
        const response = await fetch('/compile', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ code: code })
        });

        const data = await response.json();
        outputDiv.innerText = data.output;
    } catch (error) {
        outputDiv.innerText = "Error: Could not connect to the server.";
    } finally {
        btn.innerText = "Run Code ▷";
        btn.disabled = false;
        btn.style.backgroundColor = "#0e639c";
    }
}