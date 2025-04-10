# SecureChain Forensics

A blockchain-based digital evidence management system for forensic investigations.

## Setup
1. **Backend**:
   - Install Python 3.9, OpenSSL, and dependencies: `pip install -r backend/requirements.txt`.
   - Compile C++ crypto: `g++ -o build/crypto backend/crypto.cpp -lssl -lcrypto`.
   - Run Ganache: `ganache-cli`.
   - Deploy `EvidenceChain.sol` via Remix and update `EvidenceChain.json`.
   - Start Flask: `python backend/main.py`.

2. **Frontend**:
   - Install Node.js and dependencies: `cd frontend && npm install`.
   - Start React: `npm start`.

3. **Deployment**:
   - Push to GitHub and deploy via Render using `render.yaml`.

## Features
- Evidence encryption (AES-256 via C++).
- Blockchain storage (Ethereum/Ganache).
- Forensic verification and chain of custody.

- Replace `YOUR_GANACHE_PRIVATE_KEY` in `blockchain.py` with a key from Ganache.



Ensure all paths (e.g., ../build/crypto) match your local setup.



Test locally before deploying to Render.



Assets (logo.png, favicon.ico, background.jpg) need to be created or downloaded as described.



