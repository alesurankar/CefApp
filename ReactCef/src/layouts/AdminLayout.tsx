import { Navigate } from "react-router-dom";

interface AdminLayoutProps {
  user: any;
  children: React.ReactNode;
}

const AdminLayout = ({ user, children }: AdminLayoutProps) => {
  console.log("AdminLayout user:", user);
  console.log("AdminLayout role:", user?.role);

  if (!user) {
    console.log("Redirecting non-admin user");
    return <Navigate to="/" replace />;
  }

  if (user.role !== "admin") {
    console.log("Redirecting non-admin user");
    return <Navigate to="/" replace />;
  }

  console.log("Rendering admin page");
  return <div className="admin">{children}</div>;
};

export default AdminLayout;
