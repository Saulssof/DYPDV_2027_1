using UnityEngine;

public class Jugador : MonoBehaviour
{
    private void OnCollisionEnter2D(Collision2D col)
    {
        Debug.Log("Colisionando con: " + col.gameObject.name);
    }

    private void OnCollisionStay2D(Collision2D col)
    {
        Debug.Log("Aun colisionando con: " + col.gameObject.name);
    }
}