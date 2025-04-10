from flask import Flask, request, jsonify
import os
import hashlib
import subprocess
from blockchain import Blockchain

app = Flask(__name__)
blockchain = Blockchain()  # Initialize blockchain
UPLOAD_FOLDER = 'evidence'
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

# Ensure evidence directory exists
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

@app.route('/upload', methods=['POST'])
def upload_evidence():
    if 'file' not in request.files:
        return jsonify({'error': 'No file provided'}), 400
    
    file = request.files['file']
    filename = file.filename
    filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
    file.save(filepath)

    # Encrypt file using C++ binary
    encrypted_path = os.path.join(app.config['UPLOAD_FOLDER'], filename + '.enc')
    subprocess.run(['../build/crypto', 'encrypt', filepath, encrypted_path])

    # Hash the encrypted file
    with open(encrypted_path, 'rb') as f:
        file_hash = hashlib.sha256(f.read()).hexdigest()

    # Store hash on blockchain
    tx_hash = blockchain.store_evidence(file_hash, filename)

    return jsonify({
        'message': 'Evidence uploaded and secured',
        'file_hash': file_hash,
        'tx_hash': tx_hash,
        'encrypted_path': encrypted_path
    }), 200

@app.route('/verify/<file_hash>', methods=['GET'])
def verify_evidence(file_hash):
    is_valid = blockchain.verify_evidence(file_hash)
    return jsonify({'valid': is_valid}), 200

@app.route('/evidence/<filename>', methods=['GET'])
def get_evidence(filename):
    encrypted_path = os.path.join(app.config['UPLOAD_FOLDER'], filename + '.enc')
    if os.path.exists(encrypted_path):
        return jsonify({'status': 'exists', 'path': encrypted_path}), 200
    return jsonify({'error': 'File not found'}), 404

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
