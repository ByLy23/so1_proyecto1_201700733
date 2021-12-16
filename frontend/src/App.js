import { useState } from 'react';
import './App.css';
import { getKill } from './getKill';
import { getRam } from './getRam';

function App() {
  const [state, setstate] = useState(0);
  const [ram, setram] = useState({});
  const killProcess = () => {
    getKill(state).then(console.log('exito'));
  };
  const handleUpdateRam = () => {
    setTimeout(() => {
      getRam().then((data) => {
        setram(data);
        console.log(ram);
      });
    }, 3000);
  };
  return (
    <div className="App">
      <div className="nav">
        <span className="kill">
          <input
            type="text"
            className="form-control"
            onChange={(val) => setstate(val)}
            placeholder="Kill PID"
          />
          <button className="btn btn-primary" onClick={killProcess}>
            Kill
          </button>
        </span>
      </div>
      <div className="cpuModule"></div>
      <div className="ramModule">
        <button className="btn btn-primary" onClick={handleUpdateRam}>
          Actualizar Modulo Ram
        </button>
        <span></span>
      </div>
    </div>
  );
}

export default App;
