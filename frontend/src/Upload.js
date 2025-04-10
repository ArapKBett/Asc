import React, { useState } from 'react';
import axios from 'axios';

const contractABI = require('./EvidenceChain.json').abi; // Copy ABI from backend/contracts/EvidenceChain.json
const contractAddress = 'YOUR_CONTRACT_ADDRESS'; // Replace with deployed contract address

function Upload({ web3, account }) {
  const [file, setFile] = useState(null);
  const [response, setResponse] = useState(null);

  const handleFileChange = (e) => setFile(e.target.files[0]);

  const handleSubmit = async (e) => {
    e.preventDefault();
    if (!web3 || !account) {
      alert('Please connect MetaMask!');
      return;
    }

    const formData = new FormData();
    formData.append('file', file);

    try {
      // Upload file to backend
      const res = await axios.post(`${process.env.REACT_APP_API_URL}/upload`, formData);
      const { file_hash, filename } = res.data;

      // Interact with smart contract via MetaMask
      const contract = new web3.eth.Contract(contractABI, contractAddress);
      const tx = await contract.methods.storeEvidence(file_hash, filename).send({ from: account });
      
      setResponse({
        file_hash,
        tx_hash: tx.transactionHash,
        encrypted_path: res.data.encrypted_path
      });
    } catch (err) {
      console.error(err);
      alert('Error uploading or storing evidence');
    }
  };

  return (
    <div>
      <h2>Upload Evidence</h2>
      <form onSubmit={handleSubmit}>
        <input type="file" onChange={handleFileChange} style={{ color: '#00ff00' }} />
        <button type="submit" style={{ background: '#000', color: '#00ff00', border: '1px solid #00ff00' }}>
          Upload
        </button>
      </form>
      {response && (
        <div>
          <p>File Hash: {response.file_hash}</p>
          <p>Transaction Hash: {response.tx_hash}</p>
          <p>Encrypted Path: {response.encrypted_path}</p>
        </div>
      )}
    </div>
  );
}

export default Upload;
