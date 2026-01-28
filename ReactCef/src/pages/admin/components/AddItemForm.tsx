import { useState } from "react";

interface AddItemFormProps {
  onSuccess: () => void;
}

const AddItemForm = ({ onSuccess }: AddItemFormProps) => {
  const [name, setName] = useState("");
  const [price, setPrice] = useState<number | "">("");
  const [loading, setLoading] = useState(false);

    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();

        // TEMP: just verify data flow
        console.log({
            name,
            price,
        });
        onSuccess();
        // later: send to API
    };

  return (
    <form className="flex flex-col gap-2" onSubmit={handleSubmit}>
      <h2 className="text-lg font-bold mb-4">Add Item</h2>
      <input
        type="text"
        placeholder="Item Name"
        className="border p-2 rounded"
        value={name}
        onChange={(e) => setName(e.target.value)}
        required
      />
      <input
        type="number"
        placeholder="Price"
        className="border p-2 rounded"
        value={price}
        onChange={(e) => setPrice(e.target.value === "" ? "" : Number(e.target.value))}
        required
      />
      <button
        type="submit"
        className="bg-blue-500 text-white px-4 py-2 rounded mt-2"
        disabled={loading}
      >
        {loading ? "Adding..." : "Add"}
      </button>
    </form>
  );
};

export default AddItemForm;