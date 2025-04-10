import React, { useState } from 'react';
import Web3 from 'web3';

const contractData = require('./EvidenceChain.json');
const contractABI = contractData.abi;
const contractAddress = contractData.address;

function Dashboard() {
  const [hash, setHash] = useState('');
  const [result, setResult] = useState(null);

  const handleVerify = async () => {
    try {
      const web3 = new Web3('https://sepolia.infura.io/v3/e1881e44492c4f7282b95acfdb16ade1');
      const contract = new web3.eth.Contract(contractABI, contractAddress);
      const isValid = await contract.methods.verifyEvidence(hash).call();
      setResult(isValid ? 'Valid' : 'Tampered');
    } catch (err) {
      console.error(err);
      setResult('Error verifying evidence');
    }
  };

  return (
    <div>
      <h2>Forensic Dashboard</h2>
      <input
        type="text"
        value={hash}
        onChange={(e) => setHash(e.target.value)}
        placeholder="Enter file hash"
        style={{ background: '#000', color: '#00ff00', border: '1px solid #00ff00' }}
      />
      <button
        onClick={handleVerify}
        style={{ background: '#000', color: '#00ff00', border: '1px solid #00ff00' }}
      >
        Verify
      </button>
      {result && <p>Evidence Status: {result}</p>}
    </div>
  );
}

export default Dashboard;
