struct {
  double (*activation) (double);
  node** input;
  double* weights;
  int numInput;
  node** output;
  int numOutput;
  double out;
} node;

struct {
  double (*get)(void);
} output;

struct {
  double (*set)(double);
} input;

double sigmoid(double input)
{
  return 0.0;
}

double threshold(double input)
{
  return 0.0;
}

double weightedSum(node* n)
{
  double sum = 0.0;
  for(i = 0; i < n->numInput; i++)
  {
    sum += n->input[i]->out * n->weights[i];
  }
  return sum;
}

void updateOutput(node* n)
{
  n->output = n->activation(weightedSum(n));
}

node** constructNetwork(int numLayers, int* numPerlayer, int numInputs, node** inputs, int numOutput,node** outputs)
{
  node** hiddenlayer = calloc(numLayers);
  for(int i = 0; i < numLayers; i++)
  {
    hiddenlayer[i] = calloc(numPerlayer[i]);
  }
  
}

int main()
{
  node** hiddenLayers;
}
