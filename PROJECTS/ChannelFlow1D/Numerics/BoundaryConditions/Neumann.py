from pyad.pyAD import *

#--------------------------------------------------------------
# This is a second order neumann boundary condition, hence
# requiring values from two nodes adjacent to the boundary
#--------------------------------------------------------------
def neumannBC(
    inputs_AD = { 'phi_0' : [], 'phi_1':[], 'phi_2':[]},
    inputs = {'y_b':[], 'y_1':[], 'y_2':[], 'value':[]}
):
    phi_0 = inputs_AD['phi_0']
    phi_1 = inputs_AD['phi_1']
    phi_2 = inputs_AD['phi_2']
    value = inputs['value']
    h = inputs['y_1'] - inputs['y_b']
    k = inputs['y_2'] - inputs['y_b']
    #----------------------------------------------------------
    # Representing the derivative as:
    # dphi_dy = c_b*phi_b + c_1*phi_1 + c_2*phi_2
    #----------------------------------------------------------
    # Use Taylor series expansion using 'h' and 'k' as defined
    # above:
    # c_0 + c_1 + c_2 = 0 (Value itself)
    # c_1*h + c_2*k = 1 (First Derivative)
    # c_1*h**2 + c_2*k**2 = 0 (Second Derivative)
    #----------------------------------------------------------
    c_2   = h / (k * (h-k))
    c_1   = - c_2 * (k / h)**2
    c_0   = - c_1 - c_2
    R_phi = value - c_1*phi_1 - c_2*phi_2 - c_0*phi_0
    outputs = { }
    outputs_AD = { 'R_phi' : R_phi }
    return outputs, outputs_AD