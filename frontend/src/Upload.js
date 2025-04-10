import React, { useState } from 'react';
import axios from 'axios';

function Upload() {
  const [file, setFile] = useState(null);
  const [response, setResponse] = useState(null);

  const handleFileChange = (e) => setFile(e.target.files[0]);

  const handleSubmit = async (e) => {
    e.preventDefault();
    const formData = new FormData();
    formData.append('file', file);

    try {
      const res = await axios.post(`${process.env.REACT_APP_API_URL}/upload`, formData);
      setResponse(res.data);
    } catch (err) {
      console.error(err);
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
