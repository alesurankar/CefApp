import { useEffect, useState } from 'react';
import { Routes, Route } from "react-router-dom";
import AdminPage from "./pages/admin/AdminPage";
import HomePage from "./pages/public/HomePage";
import Page1 from './pages/public/Page1';
import Page2 from './pages/public/Page2';
import Page3 from './pages/public/Page3';
import PublicLayout from "./layouts/PublicLayout";
import AdminLayout from "./layouts/AdminLayout";
import api from "./utils/api";

const App = () => {
  const [user, setUser] = useState<any>(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    const fetchUser = async () => {
      try {
        const { data } = await api.get("/me");
        setUser(data.user || null);
      } catch (err) {
        setUser(null);
      } finally {
        setLoading(false);
      }
    };

    fetchUser();
  }, []);

  if (loading) {
    return <div>Loading...</div>;
  }

  return (
    <Routes>
      {/* Public pages */}
      <Route element={<PublicLayout user={user} setUser={setUser} />}>
        <Route path="/" element={<HomePage />} />
        <Route path="/page1" element={<Page1 />} />
        <Route path="/page2" element={<Page2 />} />
        <Route path="/page3" element={<Page3 />} />
      </Route>

      {/* Admin pages */}
      <Route
        path="/admin"
        element={
          <AdminLayout user={user}>
            <AdminPage />
          </AdminLayout>
        }
      />
    </Routes>
  );
};

export default App;
