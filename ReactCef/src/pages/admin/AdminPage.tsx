/**
 * Component that renders the complete admin page
 * Organizes all sections from top to bottom
 */

import Navbar from "./components/Navbar";

interface AdminPageProps {
  user?: any; // optional, but will be passed from AdminLayout
}

const AdminPage = ({ user }: AdminPageProps) => {
  return (
    <div className='main'>
      <Navbar />
      <div className="p-8">
        <h1 className="text-3xl font-bold mb-4">Admin Dashboard</h1>
        <p>Welcome, {user?.name || "Admin"}! You have admin access.</p>
      </div>
    </div>
  )
}

export default AdminPage;