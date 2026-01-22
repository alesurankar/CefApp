import React, { useEffect, useState } from "react";

// Simulated API call
const fakeApi = () =>
  new Promise<string>((resolve) => setTimeout(() => resolve("Hello from API!"), 500));

export default function App() {
  const [message, setMessage] = useState("Loading...");

  useEffect(() => {
    fakeApi().then(setMessage);
  }, []);

  return (
    <div style={{ display: "flex", justifyContent: "center", marginTop: "2rem" }}>
      <h1>{message}</h1>
    </div>
  );
}
