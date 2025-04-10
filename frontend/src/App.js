import React from 'react';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';
import Upload from './Upload';
import Dashboard from './Dashboard';
import './App.css';  // Add basic styling

function App() {
  return (
    <Router>
      <div className="App" style={{ backgroundImage: `url(/background.jpg)`, backgroundSize: 'cover' }}>
        <img src="/logo.png" alt="SecureChain Logo" style={{ width: '150px' }} />
        <h1>SecureChain Forensics</h1>
        <Switch>
          <Route exact path="/" component={Upload} />
          <Route path="/dashboard" component={Dashboard} />
        </Switch>
      </div>
    </Router>
  );
}

export default App;
