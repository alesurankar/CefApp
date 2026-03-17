import { useState } from "react"


export interface DropdownWindow {
  x: number;
  y: number;
  visible: boolean;
  type?: "viewPanel" | "other"
}

export const dropdownManager = () => {
  const [dropdown, setDropdown] = useState<DropdownWindow>({ 
    visible: false,
    x: 0, 
    y: 0,
    type: undefined
  });

  const toggleDropdown = (x: number, y: number, type?: "viewPanel" | "other") => {
    setDropdown( prev => ({ visible: !prev.visible, x, y, type }));
  };

  const showDropdown = (x: number, y: number, type?: "viewPanel" | "other") => {
    setDropdown({ visible: true, x, y, type });
  };

  const hideDropdown = () => {
    setDropdown(prev => ( { ...prev, visible: false}));
  }

  return { dropdown, toggleDropdown, showDropdown, hideDropdown }
};