#ifndef RAWMODEL_H
#define RAWMODEL_H

class RawModel {
public:
  RawModel(unsigned int vao_id, unsigned int vertex_count);
  unsigned int get_vao_id() const { return this->vao_id; }
  unsigned int get_vertex_count() const { return this->vertex_count; }

private:
  unsigned int vao_id;
  unsigned int vertex_count;
};

#endif // !RAWMODEL_H
