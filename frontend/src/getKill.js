export const getKill = async ({ estado }) => {
  const requestOps = {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ pid: estado }),
  };
  // const response = await fetch('https://backend-jolc.herokuapp.com/interpretar', requestOps);
  const response = await fetch('http://localhost:8000/mataProceso', requestOps).catch('Error'); //CAMBIAR EL OPTIMIZAR POR EL INTERPRETAR
  const data = await response.json().catch('error');
  return data;
};
