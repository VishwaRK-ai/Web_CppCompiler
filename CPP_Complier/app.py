import os
import subprocess
import uuid
import glob
from flask import Flask, render_template, request, jsonify

app = Flask(__name__)

# Load all custom headers from 'include/' directory
def load_custom_library():
    library_code = ""
    # Standard includes first
    if os.path.exists('include/std_includes.h'):
        with open('include/std_includes.h', 'r') as f:
            library_code += f.read() + "\n"

    # Load util files
    for filepath in glob.glob("include/*.h"):
        filename = os.path.basename(filepath)
        if filename == "std_includes.h": continue 
        
        with open(filepath, 'r') as f:
            library_code += f"\n// --- {filename} ---\n"
            library_code += f.read() + "\n"
            
    return library_code

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/compile', methods=['POST'])
def compile_code():
    data = request.json
    user_code = data.get('code', '')

    unique_id = str(uuid.uuid4())
    source_file = f"temp_{unique_id}.cpp"
    executable_file = f"temp_{unique_id}"

    # Inject Library
    full_source = load_custom_library() + "\n// --- USER SUBMISSION ---\n" + user_code

    # Macro expansion
    full_source = full_source.replace("@PI", "3.141592653589793")
    full_source = full_source.replace("@INF", "1e18")

    try:
        with open(source_file, 'w') as f:
            f.write(full_source)

        # Standard CP Flags: -O2 for optimization, -std=c++17
        compile_process = subprocess.run(
            ['g++', source_file, '-o', executable_file, '-std=c++17', '-O2'],
            capture_output=True,
            text=True
        )

        if compile_process.returncode != 0:
            error_msg = compile_process.stderr
            if "temp_" in error_msg:
                error_msg = error_msg.split(source_file)[-1] # Strip file path
            return jsonify({'output': f"Compilation Error:\n{error_msg}"})

        run_process = subprocess.run(
            [f'./{executable_file}'],
            capture_output=True,
            text=True,
            timeout=3
        )

        return jsonify({'output': run_process.stdout + run_process.stderr})

    except subprocess.TimeoutExpired:
        return jsonify({'output': "Time Limit Exceeded."})
    except Exception as e:
        return jsonify({'output': f"System Error: {str(e)}"})
    
    finally:
        if os.path.exists(source_file): os.remove(source_file)
        if os.path.exists(executable_file): os.remove(executable_file)

if __name__ == '__main__':
    app.run(debug=True, port=5000)