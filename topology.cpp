#include "topology.h"

using namespace std;

ToMatrix::ToMatrix(const int nbRow, const int nbCol)
    : m_nbRow(nbRow), m_nbCol(nbCol) {}
int ToMatrix::operator()(int row, int col) { return m_nbCol * row + col; }
const int ToMatrix::getRow() const { return m_nbRow; }
const int ToMatrix::getCol() const { return m_nbCol; }

bool ToMatrix::isValid(int row, int col) {
  return row > -1 && row < getRow() && col > -1 && col < getCol();
}

void print_matrix(int *matrix, ToMatrix t) {
  std::cout << "Matrix : " << t.getRow() << " - " << t.getCol() << std::endl;
  for (int i = 0; i < t.getRow(); i++) {
    for (int j = 0; j < t.getCol(); j++) {
      std::cout << matrix[t(i, j)] << " " << flush;
    }
    std::cout << std::endl;
  }
}

void changeConnected(int row, int col, int *matrix, int *matAux, ToMatrix t) {
  if (t.isValid(row + 1, col) && matAux[t(row + 1, col)] == 0 &&
      matrix[t(row + 1, col)] == 1) {
    matAux[t(row + 1, col)] = matAux[t(row, col)];
    changeConnected(row + 1, col, matrix, matAux, t);
  }
  if (t.isValid(row - 1, col) && matAux[t(row - 1, col)] == 0 &&
      matrix[t(row - 1, col)] == 1) {
    matAux[t(row - 1, col)] = matAux[t(row, col)];
    changeConnected(row - 1, col, matrix, matAux, t);
  }
  if (t.isValid(row, col + 1) && matAux[t(row, col + 1)] == 0 &&
      matrix[t(row, col + 1)] == 1) {
    matAux[t(row, col + 1)] = matAux[t(row, col)];
    changeConnected(row, col + 1, matrix, matAux, t);
  }
  if (t.isValid(row, col - 1) && matAux[t(row, col - 1)] == 0 &&
      matrix[t(row, col - 1)] == 1) {
    matAux[t(row, col - 1)] = matAux[t(row, col)];
    changeConnected(row, col - 1, matrix, matAux, t);
  }
}

int nbConnectedComponent(double *image, const int taille) {
  int compteur = 0;
  int matrix[taille * taille];
  int matAux[taille * taille];
  ToMatrix t(taille,taille);

  for (int i = 0; i < taille * taille; i++)
  {
    matAux[i] = 0;

    if (image[i] >= LIMIT_EMPTY_TOPOLOGY)
      matrix[i] = 1;
    else
      matrix[i] = 0;
  }

  for (int i = 1; i < taille; i++) {
    for (int j = 1; j < taille; j++) {
      if (matrix[t(i, j)] == 1 and matAux[t(i, j)] == 0) {
        compteur++;
        matAux[t(i, j)] = compteur;
        changeConnected(i, j, matrix, matAux, t);
      }
    }
  }

  print_matrix(matAux, t);
  std::cout << "Resultat: " << compteur << '\n';

  return compteur;
}



int nbConnectedComponentMatrix(double image[TAILLE][TAILLE])
{
    double line[TAILLE*TAILLE];

    for (int j = 0; j < TAILLE; j++)
    {
        for (int i = 0; i < TAILLE; i++)
            line[j*TAILLE + i] = image[j][i];

    }

    return nbConnectedComponent(line, TAILLE);
}