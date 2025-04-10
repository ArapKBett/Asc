import React, { useState } from 'react';
import axios from 'axios';

function Dashboard() {
  const [hash, setHash] = useState('');
  const [result, setResult] = useState(null);

  const handleVerify = async () => {
    try {
      const res = await axios.get(`${process.env.REACT_APP_API_URL}/verify/${hash}`);
      setResult(res.data.valid ? 'Valid' : 'Tampered');
    } catch (err) {
      console.error(err);
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
