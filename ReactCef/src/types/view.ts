
export type ViewKind =
  | "empty" 
  | "d3d";

export interface View {
  id: number;
  title: string;
  kind: ViewKind;
}