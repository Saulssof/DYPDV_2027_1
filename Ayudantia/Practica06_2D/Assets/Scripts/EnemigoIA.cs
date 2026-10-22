
using UnityEngine;

public class EnemigoIA : Personaje
{
    public float direccion = -1f;

    private Animator anim;

    protected override void Awake()
    {
        base.Awake();
        anim = GetComponent<Animator>();
    }

    void Update()
    {
        rb.velocity = new Vector2(
            direccion * velocidad,
            rb.velocity.y
        );

        if (direccion != 0)
        {
            sr.flipX = direccion < 0;
        }

        if (anim != null)
        {
            anim.SetBool(
                "Caminando",
                Mathf.Abs(rb.velocity.x) > 0.1f
            );
        }
    }

    void OnCollisionEnter2D(Collision2D col)
    {
        Debug.Log("Enemigo colisionó con: " + col.gameObject.name);

        if (col.gameObject.CompareTag("Pared") ||
            col.gameObject.CompareTag("Obstaculo"))
        {
            direccion *= -1;
        }

        if (col.gameObject.CompareTag("Player"))
        {
            Debug.Log("Normal de contacto: " + col.contacts[0].normal);

            if (col.contacts[0].normal.y < -0.5f)
            {
                RecibirDaño(1);
            }
            else
            {
                Jugador jugador = col.gameObject.GetComponent<Jugador>();

                if (jugador != null)
                {
                    jugador.RecibirDaño(1);
                }
            }
        }
    }
}
