import { useEffect, useState } from "react";
import { QuoteBlock, QuoteIn } from "./QuoteBlock";
import { RedNinja } from '../../../assets/images/images'
import api from '../../../utils/api';

interface Props {
  user: any;
}

const Fetch = ({ user }: Props) => {
    const [comments, setComments] = useState<any[]>([]);

    const fetchComments = async () => {
        if (!user) return;
        try {
        const { data } = await api.get("/comments");
        setComments(data.comments);
        } catch (err) {
        console.error("Failed to fetch comments:", err);
        }
    };

    useEffect(() => {
        fetchComments();
    }, [user]);

    return (
        <>
            <QuoteIn onCommentAdded={fetchComments}/>
            {comments.length === 0 ? (
                <QuoteBlock
                    key="no-comments"
                    text="No comments yet"
                    author="N/A"
                />
            ) : (
                comments.map((comment) => (
                    <QuoteBlock
                        key={comment._id}
                        text={comment.text}
                        author={comment.author}
                        image={comment.image || RedNinja}
                    />
                ))
            )}
        </>
    )
}

export default Fetch;