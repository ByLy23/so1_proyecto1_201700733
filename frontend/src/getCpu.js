export const getCpu = async () => {
  // const response = await fetch('https://backend-jolc.herokuapp.com/interpretar', requestOps);
  const response = await fetch('http://localhost:8000/iniCpu').catch('Error');
  //CAMBIAR EL OPTIMIZAR POR EL INTERPRETAR
  const data = await response.json().catch('error');
  return data;
};
