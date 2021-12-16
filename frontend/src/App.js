import { useEffect, useState } from 'react';
import './App.css';
import { getCpu } from './getCpu';
import { getKill } from './getKill';
import { getRam } from './getRam';

function App() {
  const [state, setstate] = useState(0);
  const [ram, setram] = useState({});
  const [cpu, setcpu] = useState([]);
  const killProcess = () => {
    getKill(state).then(console.log('exito'));
  };
  useEffect(() => {
    setTimeout(() => {
      getRam().then((data) => {
        setram(data);
      });
    }, 3000);
  });
  const handleUpdate = () => {
    getCpu().then((data) => {
      setcpu(data);
    });
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
      <div className="cpuModule">
        <button className="btn btn-primary" onClick={handleUpdate}>
          UpdateCpu
        </button>
        {cpu.map((element) => {
          return (
            <div>
              <p>
                <b>Memoria:</b> {element.Memoria}
              </p>
              <p>
                <b>Proceso:</b> {element.Proceso}
              </p>
              <p>
                <b>Usuario:</b> {element.Usuario}
              </p>
              <p>
                <b>PID:</b> {element.PID}
              </p>
              <div>
                {element.Childs.map((e) => {
                  return (
                    <div>
                      <p>
                        <b>Proceso Hijo: </b>
                        {e.ProcesoHijo}
                      </p>
                      <p>
                        <b>PDI Hijo: </b>
                        {e.PIDhijo}
                      </p>
                    </div>
                  );
                })}
                <hr />
              </div>
            </div>
          );
        })}
        {/* <p>Total Ram: {ram.ram}</p>
        <p>Uso: {ram.used}</p>
        <p>Porcentaje: {ram.avg}%</p> */}
      </div>
      <div className="ramModule">
        <p>Total Ram: {ram.ram}</p>
        <p>Uso: {ram.used}</p>
        <p>Porcentaje: {ram.avg}%</p>
      </div>
    </div>
  );
}

export default App;
