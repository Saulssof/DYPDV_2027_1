using UnityEngine;

public class ControlJugador : MonoBehaviour
{
    void Update()
    {
        // Movimiento horizontal
        float h = Input.GetAxis("Horizontal");

        if (h != 0)
        {
            Debug.Log("Movimiento horizontal: " + h);
        }

        // Movimiento en verticañ
        if (Input.GetKeyDown(KeyCode.Space))
        {
            Debug.Log("Salto detectado");
        }
    }
}