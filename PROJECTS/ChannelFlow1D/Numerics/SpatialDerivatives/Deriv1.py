def deriv1(
    inputs_AD = {'uL':[], 'uC':[], 'uR':[]},
    inputs    = {'yL':[], 'yC':[], 'yR':[]}
):

    leftDeriv = (inputs_AD['uC']-inputs_AD['uL']) / \
                (inputs['yC']-inputs['yL'])
    
    rightDeriv = (inputs_AD['uR']-inputs_AD['uC']) / \
                 (inputs['yR']-inputs['yC'])

    dudy = 0.5 * (leftDeriv + rightDeriv)

    outputs = { }
    outputs_AD = { 'dudy' : dudy }

    return outputs, outputs_AD