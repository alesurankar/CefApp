import { useState } from "react"


export interface DropdownWindow {
  visible: boolean;
  x: number;
  y: number;
}

export const dropdownManager = () => {
  const [dropdown, setDropdown] = useState<DropdownWindow>({ 
    visible: false, 
    x: 0, 
    y: 0 
  });

  const toggleDropdown = (x: number, y: number) => {
    setDropdown( prev => ({ visible: !prev.visible, x, y }));
  };

  const showDropdown = (x: number, y: number) => {
    setDropdown({ visible: true, x, y });
  };

  const hideDropdown = () => {
    setDropdown(prev => ( { ...prev, visible: false}));
  }

  return { dropdown, toggleDropdown, showDropdown, hideDropdown }
};